clear;

rgb1 = imread('input1.bmp');
out1 = imgeh(rgb1,1,1.5,1.1);
imwrite(out1,'output1.bmp');

rgb2 = imread('input2.bmp');
out2 = imgeh(rgb2,1,1.5,1.1);
imwrite(out2,'output2.bmp');

rgb3 = imread('input3.bmp');
out3 = imgeh(rgb3,1,1.5,1.1);
imwrite(out3,'output3.bmp');

rgb4 = imread('input4.bmp');
out4 = imgeh(rgb4,1,1.5,1.1);
imwrite(out4,'output4.bmp');