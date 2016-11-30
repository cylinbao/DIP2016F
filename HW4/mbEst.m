clear;

img = imread('input2.bmp');
ori = imread('input2_ori.bmp');

for i = 1:10
    for j = 1:15
        LEN = i*5;
        THETA = j*5;
        H = fspecial('motion',LEN,THETA);
        img_mb = imfilter(ori,H,'replicate');
        psnrTable(i,j) = psnr(img_mb, img);
        snrTable(i,j) = abs(snr(img_mb, img));
    end
end

% LEN = 10;
% THETA = 50;
% H = fspecial('motion',LEN,THETA);
% img_mb = imfilter(ori,H,'replicate');
% figure
% imshow(img);
% figure
% imshow(img_mb);