%----------------------------------------------
% Question - 1 - B
% Binary Bandit B
% Two actions 1 and 2
% Rewards are [0, 1]
% 
% steps = Number of time steps
% 
% totalValue = Total value after each time step
%
% e = epsilon value
%
%----------------------------------------------

Q=zeros(1,2);
N=zeros(1,2);
e=0.1;

for i=1:1000
    if(rand > e)
        [m,id]=max(Q);
        A=id;
    else
        temp=randperm(2);
        A=temp(1);
    end
    R = binaryBanditB(A);
    N(A)=N(A)+1;
    Q(A)= Q(A)+(R - Q(A))/N(A);
    if i==1
        avg(i)= R;
    else
        avg(i)=((i-1)*avg(i-1)+R)/i;
    end
end

plot(1:1000,avg)
ylim([0 1])

xlabel('Time Steps')
ylabel('Reward')
