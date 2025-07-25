#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include <string.h>

#include "lcd_gui.h"
#include "lcd_1.3inch.h"

IMAGE Image;
void Image_Init( uint16_t img_w, uint16_t img_h, uint16_t rotate, uint16_t mirror )
{
    Image.w = img_w;
    Image.h = img_h;
    Image.rotate = rotate;
    Image.mirror = mirror;
    if (Image.rotate == ROTATE_90 || Image.rotate == ROTATE_270)
    {
        Image.h = img_w;
        Image.w = img_h; 
    }
}
//set pixel color x:1~320 y:1~240
void Gui_set_pix(uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t xx=0;
    uint16_t yy=0;
    if(x>Image.w || y>Image.h)
    {
        //printf("ERR:set_pix point out of screen area!\r\n");
        return ;
    }
    switch(Image.rotate)
    {
        case ROTATE_0:
            xx = x;
            yy = y;
            break;
        case ROTATE_90:
            xx = LCD_W-y-1;
            yy = x;
            break;
        case ROTATE_180:
            xx = LCD_W-x-1;
            yy = LCD_H-y-1;
            break;
        case ROTATE_270:
            xx = y;
            yy = LCD_H-x-1;
            break;
        default:
            return ;
    }
    if(xx > LCD_W || yy > LCD_H)
    {
        return;
    }
    Draw_Point( xx, yy, color);
}

void Gui_draw_point(uint16_t x, uint16_t y, uint16_t color, uint16_t width)
{
    uint16_t xd, yd;
    if(x>Image.w || y > Image.h)
    {
        return ;
    }
    for(xd = 0;xd<width; xd++)
    {
        for(yd=0;yd<width; yd++)
        {
            if(x+xd>Image.w || y+yd>Image.h )
            {
               continue;    
            }
            Gui_set_pix(x+xd-1, y+yd-1, color);     
        }
    }
}

//clear the whole screen
void Gui_Clear( uint16_t color)
{
    uint16_t x,y;
    Set_Window(0, 0, LCD_H, LCD_W);
    for (y = 0; y < LCD_H; y++) 
    {
        for (x = 0; x < LCD_W; x++) 
        {
            Spi_write_word(color);
        }
    }
}

//Bresenham algorithm draw line
void Gui_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t width, LINE_STYLE type)
{
    uint16_t x = x1;
    uint16_t y = y1;
    int dx = x2-x1>=0?x2-x1:x1-x2;
    int dy = y2-y1>=0?y2-y1:y1-y2;
    int p = dx-dy;
    int e2;
    int xdir = x1>x2?-1:1;
    int ydir = y1>y2?-1:1;
    int dot_cnt = 0;
    for(;;)
    {
        dot_cnt++;
        if(type==DOTTED && dot_cnt%2==0)
        {
            Gui_draw_point(x, y, color, width);
        }
        else if(type==SOLID)
        {
            Gui_draw_point(x, y, color, width);
        }
        if(x==x2 && y==y2)
        {
            break;
        }
        e2 = 2*p;
        if(e2>= -dy)
        {
            p -= dy;
            x += xdir;
        }
        if(e2<=dx)
        {
            p += dx;
            y += ydir;
        }
    }
}

void Gui_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t width, FILL fill)
{
    uint16_t i;
    if(x1>Image.w || y1 > Image.h || x2 > Image.w || y2 > Image.h)
    {
        printf("ERR:line point out of screen area!\r\n");
        return ;
    } 
    if(fill == FULL)
    {
        for(i=y1;i<y2;i++)
        {
            Gui_draw_line(x1, i, x2, i, color, width, SOLID);
        }
    }
    else if(fill==EMPTY)
    {
        Gui_draw_line(x1, y1, x2, y1, color, width, SOLID);
        Gui_draw_line(x1, y1, x1, y2, color, width, SOLID);
        Gui_draw_line(x1, y2, x2, y2, color, width, SOLID);
        Gui_draw_line(x2, y1, x2, y2, color, width, SOLID);
    }
}

//Bresenham  algorithm draw circle
void Gui_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color, uint16_t width, FILL fill)
{
    uint16_t dx=0,dy=r;
    int d = 1-r;
    uint16_t i;
    if(x>Image.w || y > Image.h)
    {
        printf("ERR:circle center point out of screen area!\r\n");
        return ;
    } 
    while(dy>dx)
    {
        if(fill==EMPTY)
        {
            Gui_draw_point(x+dx, y+dy, color, width);
            Gui_draw_point(x+dy, y+dx, color, width);
            Gui_draw_point(x-dx, y+dy, color, width);
            Gui_draw_point(x-dy, y+dx, color, width);
            Gui_draw_point(x-dx, y-dy, color, width);
            Gui_draw_point(x-dy, y-dx, color, width);
            Gui_draw_point(x+dx, y-dy, color, width);
            Gui_draw_point(x+dy, y-dx, color, width);
        }
        else if(fill==FULL)
        {
            for(i=dx;i<=dy;i++)
            {
                Gui_draw_point(x+dx, y+i, color, width);
                Gui_draw_point(x+i, y+dx, color, width);
                Gui_draw_point(x-dx, y+i, color, width);
                Gui_draw_point(x-i, y+dx, color, width);
                Gui_draw_point(x-dx, y-i, color, width);
                Gui_draw_point(x-i, y-dx, color, width);
                Gui_draw_point(x+dx, y-i, color, width);
                Gui_draw_point(x+i, y-dx, color, width);                
            }
        }
        if(d<0)
        {
            d += 2*dx+3;    
        }
        else
        {
            d += 2*(dx-dy)+5;
            dy--;
        }
        dx++;
    }
}


void Gui_draw_char(uint16_t x, uint16_t y, const char str_char, FONT* Font, uint16_t color, uint16_t background)
{
    uint16_t row, col_bit;

    if (x > Image.w || y > Image.h) 
    {
        printf("ERR:draw char point out of screen area!\r\n");
        return;
    }
    //the number of bytes occupied by a character
    uint16_t char_nbytes = Font->h * (Font->w / 8 + (Font->w % 8 ? 1 : 0));

    //the offset of the character
    uint32_t offset = (str_char - ' ') * char_nbytes;
    const unsigned char *ptr = &Font->table[offset];
    for (row = 0; row < Font->h; row ++) 
    {
        for (col_bit = 0; col_bit < Font->w; col_bit++ )
        {
            if (FONT_BACKGROUND == background) 
            { 
                if (pgm_read_byte(ptr) & (0x80 >> (col_bit % 8)))
                {
                    Gui_set_pix(x+col_bit, y+row, color);
                }
            } 
            else 
            {
                if (pgm_read_byte(ptr) & (0x80 >> (col_bit % 8))) 
                {
                    Gui_set_pix(x+col_bit, y+row, color);
                } 
                else 
                {
                    Gui_set_pix(x+col_bit, y+row, background);
                }
            }            
            if (col_bit % 8 == 7) //next byte
            {
                ptr++;
            }
        }
        if(Font->w % 8 != 0)// next line
        {
            ptr++;
        }
    }
}

void Gui_draw_str(uint16_t x, uint16_t y, const char *str_char, FONT* Font, uint16_t color, uint16_t background)
{
    uint16_t dx = x,dy = y;
    while(*str_char != '\0')
    {
        if((dx+Font->w)>Image.w)//wrap the line if the x direction has reached the boundary
        {
            dx = x;
            dy += Font->h;
        }
        if((dy+Font->h)>Image.h)//wrap the line if the y direction has reached the boundary
        {
            dy = y;
            dx += Font->w;
        }
        Gui_draw_char(dx, dy, *str_char++, Font, color, background);
        dx += Font->w;
    }

}

void Gui_draw_str_cn(uint16_t x, uint16_t y, const char *str_cn, CN_FONT* Font, uint16_t color, uint16_t background)
{
    uint16_t dx = x,dy = y;
    const char *p_str;
    uint16_t i,row,col_bit;
    while(*str_cn != '\0')
    {
        for(i=0;i<Font->fsize;i++)
        {
            if(((*str_cn)&0xff) == pgm_read_byte(&Font->table[i].context[0]) && (*(str_cn+1)&0xff) == pgm_read_byte(&Font->table[i].context[1])) // one chinese character occupies 2 bytes
            {
                p_str = &Font->table[i].pix[0];
                if((dx+Font->w)>Image.w)//wrap the line if the x direction has reached the boundary
                {
                    dx = x;
                    dy += Font->h;
                }
                if((dy+Font->h)>Image.h)//wrap the line if the y direction has reached the boundary
                {
                    dy = y;
                    dx += Font->w;
                }
                for (row = 0; row < Font->h; row ++) 
                {
                    for (col_bit = 0; col_bit < Font->w; col_bit++ )
                    {
                        if (FONT_BACKGROUND == background) 
                        { 
                            if (pgm_read_byte(p_str) & (0x80 >> (col_bit % 8)))
                                Gui_set_pix(dx+col_bit, dy+row, color);
                        } 
                        else 
                        {
                            if (pgm_read_byte(p_str) & (0x80 >> (col_bit % 8))) 
                            {
                                Gui_set_pix(dx+col_bit, dy+row, color);
                            } 
                            else 
                            {
                                Gui_set_pix(dx+col_bit, dy+row, background);
                            }
                        }            
                        if (col_bit % 8 == 7) //next byte
                            p_str++;
                    }
                    if(Font->w % 8 != 0)// next line
                        p_str++;
                }
                break;
            }
        }
        str_cn += 3;
        dx += Font->w;
    }
}

//show the image to part of the screen 
int Gui_show_bmp(const unsigned char *img, uint16_t x, uint16_t y, uint16_t img_w, uint16_t img_h)
{
    uint16_t i,j;
    unsigned char color_h,color_l;
    for(i=0;i<img_h;i++)
    {
       for(j=0;j<img_w;j++)
       {
           color_h = pgm_read_byte(img+i*img_w*2 + j*2+1);
           color_l = pgm_read_byte(img+i*img_w*2 + j*2);
           Gui_set_pix(x+j, y+i, (color_h<<8)|color_l);
       }  
    }
}
