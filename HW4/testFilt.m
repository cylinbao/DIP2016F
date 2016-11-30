clear; 

img1 = imread('input2.bmp');
ori1 = imread('input2_ori.bmp');
psnr_ori = psnr(img1, ori1)

LEN = 10;
THETA = 45;
PSF = fspecial('motion', LEN, THETA);
noise_var = 0.001;
wnr1 = deconvwnr(img1,PSF,noise_var);
psnr_wnr1 = psnr(wnr1,ori1)

reg1 = deconvreg(img1,PSF,1);
psnr_reg1 = psnr(reg1,ori1)

luc1 = deconvlucy(img1,PSF,10);
psnr_luc1 = psnr(luc1,ori1)

figure
subplot(221);
imshow(img1);
title('input image');
subplot(222);
imshow(wnr1);
title('Wiener filter');
subplot(223);
imshow(reg1);
title('Regularized filter');
subplot(224);
imshow(luc1);
title('Lucy-Richardson Method');