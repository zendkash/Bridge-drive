%http://stackoverflow.com/questions/23688688/how-to-do-an-animated-plot-in-matlab

filename='Swervetest.gif'
A=importdata('Swervetest.txt');
left=A.data(1:end,1:2);
right=A.data(1:end,3:4);
xvals=A.data(1:end,[1 3]);
yvals=A.data(1:end,[2 4]);
close all
figure()
hold on
axis([min(xvals(:)) max(xvals(:)) min(yvals(:)) max(yvals(:))]);

leftplot=scatter(NaN,NaN,'.');
rightplot=scatter(NaN,NaN,'.');

for ii=1:10:length(xvals)
    set(leftplot, 'XData', left(1:ii,1), 'YData', left(1:ii,2));
    set(rightplot, 'XData', right(1:ii,1), 'YData', right(1:ii,2));
    drawnow
    frame = getframe(1);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
    if ii == 1;
        imwrite(imind,cm,filename,'gif','DelayTime',0,'Loopcount',inf);
    else
        imwrite(imind,cm,filename,'gif','DelayTime',0,'WriteMode','append');
    end
end