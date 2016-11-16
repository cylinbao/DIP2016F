clear;

rgb = imread('input3.bmp');
out(:,:,1) = myhisteq(rgb(:,:,1));
out(:,:,2) = myhisteq(rgb(:,:,2));
out(:,:,3) = myhisteq(rgb(:,:,3));

figure
imshow(rgb);
figure
imshow(out);