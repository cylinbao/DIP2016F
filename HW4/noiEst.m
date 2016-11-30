clear;

img = imread('input3.bmp');
ori = imread('input3_ori.bmp');

% LEN = 15;
% THETA = 70;
% PSF = fspecial('motion', LEN, THETA);
%noise = 0.00000001;
SIGMA = 30;
[x y z] = size(img);
H = getGauBlurH(x,y,SIGMA);
noise = 0.01;
figure;
K = noise;
for i = 1:10
    K = i*noise;
    res = mydeconvwnr(img,H,K);
    psnrTable1(i) = psnr(res, ori);
%     K = K+0.01;
%     subplot(3,3,i);
%     imshow(res);
    filename = sprintf('output3_%d.bmp',i);
    imwrite(res,filename);
end
