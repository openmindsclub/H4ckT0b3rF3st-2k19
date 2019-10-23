import pygame
import time
pygame.init()

window = pygame.display.set_mode((1000,600))
pygame.display.set_caption("Tux's Journey")

x = 200
y = 400

velocity = 1
height = 70
width = 30
reach = 1

jump = False
heightreached = False
duck = False

dheight = height /2
iheight = 70
dy = y + dheight

loop = True
while loop:
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT: loop = False

        if event.type == pygame.KEYDOWN:

            if event.key == pygame.K_DOWN and event.type == pygame.KEYDOWN and not jump and not duck: duck = True
                
            if event.key == pygame.K_UP and not jump and not duck:
                jump =  True
                basey = y
        
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_DOWN: duck = False
    if jump:
        if not heightreached:
            y -= reach
            if y == basey - (height * 2):
                heightreached = True
        else:
            y += reach
            
            if y == basey: 
                jump = False
                heightreached = False
    
    if duck:
        y = dy
        height = dheight
    elif not jump:
            y = 400
            height = iheight
    
    window.fill((255, 255, 255))
    pygame.draw.rect(window, (0, 0, 0),(x, y, width, height))
    pygame.draw.line(window, (0, 0, 0), (0, 400 + iheight), (1000, 400 + iheight))
    pygame.display.update()
    time.sleep(0.0001)

pygame.quit()