## CORONASIMULATE  Simulate coronagraph and Gerchberg-Saxton algorithm
#
# A simulation of a coronagraph and the Gerchberg-Saxton algorithm, in the
# context of NASA's Roman Space Telescope, developed to help teach ENCMP
# 100 Computer Programming for Engineers at the University of Alberta. The
# program saves output figures to PNG files for subsequent processing.
#
# Copyright (c) 2022, University of Alberta
# Electrical and Computer Engineering
# All rights reserved.
#
# Student name:
# Student CCID:
# Others:
#
# To avoid plagiarism, list the names of persons, Version 0 author(s)
# excluded, whose code, words, ideas, or data you used. To avoid
# cheating, list the names of persons, excluding the ENCMP 100 lab
# instructor and TAs, who gave you compositional assistance.
#
# After each name, including your own name, enter in parentheses an
# estimate of the person's contributions in percent. Without these
# numbers, adding to 100%, follow-up questions will be asked.
#
# For anonymous sources, enter pseudonyms in uppercase, e.g., SAURON,
# followed by percentages as above. Email a link to or a copy of the
# source to the lab instructor before the assignment is due.
#
import matplotlib.pyplot as plt
import numpy as np

def main():
    im = loadImage('300_26a_big-vlt-s.jpg')
    (im,Dphi) = opticalSystem(im,300)
    images = gerchbergSaxton(im,10,Dphi)
    saveFrames(images)

def loadImage(name):
    im = plt.imread(name)/255
    if len(im.shape) > 2:
        im = (im[:,:,0]+im[:,:,1]+im[:,:,2])/3
    im[im < 0] = 0
    im[im > 1] = 1
    return im

def opticalSystem(im,width):
    im = occultSquare(im,width)
    (IMa,IMp) = dft2(im)
    rng = np.random.default_rng(12345)
    imR = rng.random(im.shape)
    (_,Dphi) = dft2(imR)
    im = idft2(IMa,IMp-Dphi)
    return (im,Dphi)


def occultSquare(im,width):
    [lengthofimage, widthofimage] = np.shape(im)
    initiallength = int((lengthofimage/2)-(width/2))
    initialwidth = int((widthofimage/2)-(width/2))
    finallength = int((lengthofimage/2)+(width/2))
    finalwidth = int((widthofimage/2)+(width/2))
    im[initiallength:finallength,initialwidth:finalwidth] = 0
    return im

# (IMa,IMp) = dft2(im) returns the amplitude, IMa, and phase, IMp, of the
# 2D discrete Fourier transform of a grayscale image, im. The image, a 2D
# array, must have entries between 0 and 1. The phase is in radians.
def dft2(im):
    IM = np.fft.rfft2(im)
    IMa = np.abs(IM)
    IMp = np.angle(IM)
    return (IMa,IMp)

# im = idft2(IMa,IMp) returns a grayscale image, im, with entries between
# 0 and 1 that is the inverse 2D discrete Fourier transform (DFT) of a 2D
# DFT specified by its amplitude, IMa, and phase, IMp, in radians.
def idft2(IMa,IMp):
    IM = IMa*(np.cos(IMp)+1j*np.sin(IMp))
    im = np.fft.irfft2(IM)
    im[im < 0] = 0
    im[im > 1] = 1
    return im

def gerchbergSaxton(im,maxIters,dphi):
    (IMa,IMp) = dft2(im)
    images = []
    for k in range(maxIters+1):
        im = idft2(IMa,IMp + (k/maxIters)*dphi)
        images.append(im)
    return images

def saveFrames(images):
    shape = (images[0].shape[0],images[0].shape[1],3)
    image = np.zeros(shape,images[0].dtype)
    maxIters = len(images)-1
    for k in range(maxIters+1):
        for i in range(3):
            image[:,:,i] = images[k]
        plt.imshow(image)
        plt.title("Iteration %s of 10" %str(k))
        ax = plt.gca()
        ax.xaxis.set_visible(False)
        ax.yaxis.set_visible(False)
        plt.savefig('coronagraph'+str(k)+'.png')
        plt.show()

main()

#what was added was the were certain commands under the functions 'occultSquare' and 'saveFrames'. under the function 'occultSquare', we create the second
#argument called width. what the function does with these 2 arguments would be to make the centre of the image a black object. what you do to acheive this
#subtracting half the width from the width, as well as with length. in the saveFrames function, this will make the images titled properly from 1 through 10
#this will also hide the x and y axis from the images depicted which could be found at the right hand side in the console.
