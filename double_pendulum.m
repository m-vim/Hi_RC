%solving the double pendulum using rk4 type integration methods, I have converted 
%coupled 2nd order pendulum equations to a system of first order equations on paper elsewhere
%program animates double pendulum or else plots time vs angle with respect to gravity

clear all;
close all;

%constants
m1 = 2;
m2 = 1;
l1 = 1.4;
l2 = 2;
g = 9.8;
M = m1+m2;
L = l1+l2;

%define primitive functions (what a mess)
dth = @(t,y) [y(3) - y(1)];
y2_dot_num = @(t,y) [m2*l1*y(2).^2.*sin(dth(t,y)).*(l1*cos(dth(t,y))+l2) + l1*g*(m2*cos(dth(t,y)).*sin(y(3)) - m1*sin(y(1)))];
y2_dot_denom = @(t,y) [M*l1^2 - m2*l1^2*cos(dth(t,y)).^2];
y2_dot = @(t,y) [y2_dot_num(t,y)./y2_dot_denom(t,y)];
y4_dot = @(t,y) [-(l1/l2)*y2_dot(t,y).*cos(dth(t,y)) - (l1/l2)*y(2).^2.*sin(dth(t,y))-(g/l2)*sin(y(3))];

%this function is for solving the ODE
pend = @(t,y) [y(2); y2_dot(t,y); y(4); y4_dot(t,y)];

%this call solves the ODE
[t,x] = ode45 (pend, [0, 30], [1.5, 1, pi, -1]);

%second solution with nearly identical initial conditions
[t1,x1] = ode45 (pend, [0, 30], [1.5, 1, pi+.01, -1]);


%plot the angles of the two rods as a function of time
##figure(1)
##plot(t,x(:,1))
##hold on;
##plot(t,x(:,3),'r')

%this piece creates a linear interpolation of the solution so that I have angles at time points which are linearly spaced
t_int = linspace(0,30,250);
x = interp1(t,x,t_int);
x1 = interp1(t1,x1,t_int);

%here I calculate the spatial coordinates of the two masses given the angles
m1x = l1*sin(x(:,1)); %location of first mass defined relative to origin (0,0)
m1y = -l1*cos(x(:,1));
m2x = l2*sin(x(:,3)); %location of second mass defined relative to first mass
m2y = -l2*cos(x(:,3));

%same deal but for the second solution
m1x1 = l1*sin(x1(:,1));
m1y1 = -l1*cos(x1(:,1));
m2x1 = l2*sin(x1(:,3));
m2y1 = -l2*cos(x1(:,3));


%for loop generating plots showing two rotating arms of the double pendulum
for m = 1:size(x,1)
figure(1); clf; title(m); hold on; axis equal;
axis(1.5*[-L L -L L]); %the extent of the plot is set to be 1.5x the length of the summation of both rods
line([0 m1x(m,1)], [0 m1y(m,1)]); %drawing line of first rod
line([m1x(m,1) m1x(m,1)+m2x(m,1)], [m1y(m,1) m1y(m,1)+m2y(m,1)]); %line of second rod
line([0 m1x1(m,1)], [0 m1y1(m,1)], "color", "r"); %drawing lines for rods of second solution
line([m1x1(m,1) m1x1(m,1)+m2x1(m,1)], [m1y1(m,1) m1y1(m,1)+m2y1(m,1)], "color", "r");
pause(0.05); %pause for a moment before looping to next figure drawing
m
end
