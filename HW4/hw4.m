clear;

img = imread('input1.bmp');
ori = imread('input1_ori.bmp');
SIGMA = 65;
noise = 0.05;
[x y z] = size(img);
H = getGauBlurH(x,y,SIGMA);
% imgfft = imgfftresult(img1);
% compImg(imgfft,H1);
rest = mydeconvwnr(img,H,noise);
psnrValue(1,1) = psnr(img,ori);
psnrValue(1,2) = psnr(rest,ori);
%compImg(img,rest);
imwrite(rest,'output1.bmp');

img = imread('input2.bmp');
ori = imread('input2_ori.bmp');
LEN = 15;
THETA = 70;
noise = 0.05;
[x y z] = size(img);
H = getMotionBlurH(x,y,LEN,THETA);
rest = mydeconvwnr(img,H,noise);
psnrValue(2,1) = psnr(img,ori);
psnrValue(2,2) = psnr(rest,ori);
% compImg(img,rest);
imwrite(rest,'output2.bmp');

img = imread('input3.bmp');
ori = imread('input3_ori.bmp');
SIGMA = 30;
noise = 0.1;
[x y z] = size(img);
H = getGauBlurH(x,y,SIGMA);
% imgfft = imgfftresult(img3);
% compImg(imgfft,H3);
rest = mydeconvwnr(img,H,noise);
psnrValue(3,1) = psnr(img,ori);
psnrValue(3,2) = psnr(rest,ori)
% compImg(img,rest);
imwrite(rest,'output3.bmp');
clear;