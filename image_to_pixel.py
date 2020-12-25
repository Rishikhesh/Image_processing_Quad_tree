from PIL import Image
im = Image.open(r"E:\semester\sem 3\ADS\pacakge\original_image.png")

pix = list(im.getdata())

file1 = open(r"E:\semester\sem 3\ADS\pacakge\image.txt","w")

for i in pix:
    file1.write(str(i))
    file1.write('\n')
    