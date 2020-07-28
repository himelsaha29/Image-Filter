# Image-Filter

This program applies filters to images. Like those in Instagram or any other image processing applications. The program is capable to apply grayscale, sepia, blur and reflect filters to the image provided by the user as command line input and saves the resulting image as a separate file.

Usage: ./filter -[first letter of filter name] [input image address] [output image address (including file name and extension)]
Example: ./filter -r image.bmp reflected.bmp 

The algorithm:

# Grayscale: 
To apply the grayscale effect, the average of red, blue, and green values of a pixel are taken and the new value (same) is assigned back to the red, green, and blue values of the same pixel , for every pixel in the image. The concept comes from the fact that if the red, green, and blue values of a pixel are all 0, the pixel represents black, and if the values are all 255, the pixel represents white. In between the extremes, are the varying shades of gray. So the red, gree, and blue values all need to be same.

# Sepia: 
For this effect, the red, green, and blue channels of each pixel is assigned a new value which is calculated by the following formula:

  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
  
# Reflection: 
This effect involves swapping the individual pixels of an image to its symmetrically (vertical orientation) opposite one for reflection along the vertical axis.

# Blur: 
Each pixel is given a new RGB value by taking average of the RGB values of the pixels around it that are within 1 row and 1 column (itself included). This can be imagined by 3x3 boxes for pixels rounghly in the middle of the image and 2x3 or 3x2 or 2x2 boxes for pixels on the edges.
