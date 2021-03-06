%http://stackoverflow.com/questions/23688688/how-to-do-an-animated-plot-in-matlab

filename='Swervetest2.gif';
A=importdata('Swervetest2.txt');
left=A.data(1:end,1:2);
right=A.data(1:end,3:4);
xvals=A.data(1:end,[2 4]);
yvals=A.data(1:end,[1 3]);
close all
figure()
title('Simulated Bridge Trajectory Plot');
xlabel('X-position (m)');
ylabel('Y-position (m)');
hold on
leftplot=scatter(left(1:end,2),left(1:end,1),1,'.');
rightplot=scatter(right(1:end,2),right(1:end,1),1,'.');
legend('Left Front Wheel Position','Right Front Wheel Position','Location','SouthOutside');
hold off
axis equal
axis([min(xvals(:)) max(xvals(:)) min(yvals(:))-10 max(yvals(:))+10]);

for ii=1:10:length(xvals)
    set(leftplot, 'XData', left(1:ii,2), 'YData', left(1:ii,1));
    set(rightplot, 'XData', right(1:ii,2), 'YData', right(1:ii,1));
    drawnow
    frame = getframe(1);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
    if ii == 1
        imwrite(imind,cm,filename,'gif','DelayTime',0,'Loopcount',inf);
    else
        imwrite(imind,cm,filename,'gif','DelayTime',0,'WriteMode','append');
    end
end