% Question - 2
% 10 armed Bandit
% Two actions 1 and 2
% Rewards are non-stationary
% Rewards are normally distributed increment with mean zero
% and standard deviation 0.01
% steps = Number of time steps
% 
%
% e = epsilon value = 0.1
%----------------------------------------------

steps = 1000;
rewards = zeros(steps, 2);
i = 1;
totalValue = zeros(steps);
cntActions = zeros(10);

totalValue(:,i) = 0;
rewards(:, :, i) = 0;
step = 1;
cntActions(:,i) = 0;
    
while step <= steps
        
% When random no. between 0 to 1 is less than e, then perform exploration
if rand < e || step == 1
    action = randi(10);
    value = bandit(action);
    totalValue(step,i) = value;
    if step > 1
         totalValue(step,i) = totalValue(step,i) + totalValue(step - 1,i);
    end
        rewards(step, :, i) = [value, action];
            
 % When random no. between 0 to 1 is less than e, then perform exploitation
else
    actions = zeros(10, 2);
            
     for s = 1:(step)
          actions(rewards(s,2,i), 1) = actions(rewards(s,2,i),1)+rewards(s,1,i);
          actions(rewards(s,2,i), 2) = actions(rewards(s,2,i),2)+1;
     end
     
     action = 1;
     expReturn = 0;
     a = 1;
      for aa = actions
         temp = aa(1) / aa(2);
            if temp > expReturn
                expReturn = temp;
                action = a;
              end
           a = a + 1;
        end
            
       value = bandit(action);
       totalValue(step,i) = value + totalValue(step - 1,i);
       rewards(step, :, i) = [value, action];
       cntActions(:,i) = actions(:,2);
    end    
        
  step = step + 1;
end

avgReward = zeros(steps)
for i = 1:steps
    avgReward(i) = totalValue(i,2) / i
end

figure(1)
plot(avgReward(:,1))
xlabel('Time Steps')
ylabel('Average Reward')
title('10 armed Bandit')