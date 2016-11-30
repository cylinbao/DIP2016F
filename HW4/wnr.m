function [res] = wnr(img,X,Y,noise)

%img = imread('input2.bmp');

LEN = X;
THETA = Y;
PSF = fspecial('motion', LEN, THETA);

res = mydeconvwnr(img,PSF,noise);

end