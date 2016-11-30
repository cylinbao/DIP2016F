clear;

img = imread('input1.bmp');
ori = imread('input1_ori.bmp');

for i = 1:20
    sigma = i;
    img_gb = myimgaussfilt(ori,sigma);
    psnrTable(i) = psnr(img_gb, img);
    snrTable(i) = abs(snr(img_gb, img));
    fn = sprintf('output1_%d.bmp',i);
    imwrite(img_gb,fn);
end

% sigma = 20;
% img_gb = imgaussfilt(ori,sigma);
% figure
% imshow(img);
% figure
% imshow(img_gb);