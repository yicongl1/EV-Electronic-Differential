import pygame
import time
pygame.init()
screen = pygame.display.set_mode((600, 600))
background = pygame.image.load('背景.png')


class Car:
    def __init__(self, pos):
        self.image1 = pygame.image.load('速度0.png')
        self.image2 = pygame.image.load('速度中.png')
        self.image3 = pygame.image.load('速度高.png')
        self.width = 50
        self.height = 50
        self.pos = pos
        if self.pos == 0:
            self.x = 50
            self.y = 50
        elif self.pos == 1:
            self.x = 450
            self.y = 50
        elif self.pos == 2:
            self.x = 50
            self.y = 450
        elif self.pos == 3:
            self.x = 450
            self.y = 450
        self.v = 0
        self.a = 0
        self.turn = 0
        self.angle = 0

    def rotate1(self):
        self.image1 = pygame.image.load('速度0.png')
        old_core = self.image1.get_rect().center
        self.image1 = pygame.transform.rotate(self.image1, self.angle)
        return old_core

    def rotate2(self):
        self.image2 = pygame.image.load('速度中.png')
        old_core = self.image2.get_rect().center
        self.image2 = pygame.transform.rotate(self.image2, self.angle)
        return old_core

    def rotate3(self):
        self.image3 = pygame.image.load('速度高.png')
        old_core = self.image3.get_rect().center
        self.image3 = pygame.transform.rotate(self.image3, self.angle)
        return old_core

    def blit(self):
        if self.v <= 10:
            old_core = self.rotate1()
            screen.blit(self.image1, (self.image1.get_rect(center=old_core).x+self.x, \
                                      self.image1.get_rect(center=old_core).y+self.y))
        elif self.v <= 20:
            old_core = self.rotate2()
            screen.blit(self.image2, (self.image1.get_rect(center=old_core).x + self.x, \
                                      self.image1.get_rect(center=old_core).y + self.y))
        else:
            old_core = self.rotate3()
            screen.blit(self.image3, (self.image1.get_rect(center=old_core).x + self.x, \
                                      self.image1.get_rect(center=old_core).y + self.y))
        take_font = pygame.font.SysFont("arial", 40)
        position = take_font.render(f'v: {int(self.v)}', True, (0, 0, 0))
        screen.blit(position, (self.x, self.y + 110))

    def update_a(self, down, turn):
        if down == 1:
            if turn == 2:
                self.a = 5/60
            if turn == 1:
                if self.pos == 0 or self.pos == 2:
                    if self.v > 10:
                        self.a += 5/60
                    self.turn = 1
                if self.pos == 0 or self.pos == 1:
                    if self.angle >= -30:
                        self.angle += -1
            if turn == -1:
                if self.pos == 1 or self.pos == 3:
                    if self.v > 10:
                        self.a += 5/60
                    self.turn = -1
                if self.pos == 0 or self.pos == 1:
                    if self.angle <= 30:
                        self.angle += 1
        if down == 0:
            self.a = 0
            self.v = 0
            self.turn = 0
            self.angle = 0


    def update_v(self, down, key):
        self.update_a(down, key)
        self.v += self.a
        if self.v >= 20 and self.turn == 0:
            self.v = 20
        if self.v >= 30:
            self.v = 30

class Direct:
    def __init__(self):
        self.image = [pygame.image.load('上.png'), pygame.image.load('左.png'), pygame.image.load('右.png')]

    def blit(self, key, turn):
        if key == 1:
            if turn == 2:
                screen.blit(self.image[0], (250, 250))
            elif turn == -1:
                screen.blit(self.image[1], (250, 250))
            elif turn == 1:
                screen.blit(self.image[2], (250, 250))


hero = [Car(i) for i in range(4)]
dir = Direct()
key_down = 0
direct = 0
while True:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            key_down = 1
            if event.key == pygame.K_d:
                direct = 1
            if event.key == pygame.K_a:
                direct = -1
            if event.key == pygame.K_w:
                direct = 2
        if event.type == pygame.KEYUP:
            key_down = 0

        if event.type == pygame.QUIT:
            exit()
    screen.blit(background, (0, 0))
    for i in range(4):
        hero[i].update_v(key_down, direct)
        hero[i].blit()
    dir.blit(key_down, direct)
    pygame.display.update()
    time.sleep(1 / 60)