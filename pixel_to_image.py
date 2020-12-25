from PIL import Image
im = Image.open(r"E:\semester\sem 3\ADS\pacakge\original_image.png")

pix_val=[]

file2 = open(r"E:\semester\sem 3\ADS\pacakge\op_pixel.txt","r")
for i in file2:
    pix_val.append(int(i))

    
width, height = im.size

pix_val = [pix_val[i * width:(i + 1) * width] for i in range(height)]

pixels_out = []

for row in pix_val:
    for tup in row:
        pixels_out.append(tup)
        
image_out = Image.new(im.mode,im.size)
image_out.putdata(pixels_out)

image_out.save(r"E:\semester\sem 3\ADS\pacakge\edited_image.png")