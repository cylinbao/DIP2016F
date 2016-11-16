function [out] = imgeh(rgb, gsigma, shrad, shamo)

figure();
subplot(221)
imshow(rgb);
title('original');

outHis(:,:,1) = myhisteq(rgb(:,:,1));
outHis(:,:,2) = myhisteq(rgb(:,:,2));
outHis(:,:,3) = myhisteq(rgb(:,:,3));

subplot(222)
imshow(outHis);
title('histogram equalization');

outBlur = imgaussfilt(outHis,gsigma);
% H = fspecial('average');
% outBlur = imfilter(outHis, H, 'replicate');
% outBlur(:,:,1) = medfilt2(outHis(:,:,1));
% outBlur(:,:,2) = medfilt2(outHis(:,:,2));
% outBlur(:,:,3) = medfilt2(outHis(:,:,3));
subplot(223)
imshow(outBlur);
title('blur');

out = imsharpen(outBlur,'Radius',shrad,'Amount',shamo);
subplot(224)
imshow(out);
title('sharpen');

end