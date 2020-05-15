W=[1 1 1];
j=[1 2 1 2 3 4];
L=[1 1 0 0;0 1 1 1;1 0 1 0.5];
for t=1:6
        for i=1:3
       
            sum1=(W(1)+W(2)+W(3));
            p(i)=(W(i)/sum1);
            x=j(t);
            W(i)=0.5^L(i,x)*(W(i));
    
            
        end
    disp(p);
    disp(W)
    
end
    
        