S=[0 1 1 0 0 0 0 0 0;1 0 1 1 0 0 0 0 0;1 1 0 0 0 0 1 0 0;0 1 0 0 1 1 0 0 0;0 0 0 1 0 1 0 0 0;0 0 0 1 1 0 0 1 0;0 0 1 0 0 0 0 1 1;0 0 0 0 0 1 1 0 1;0 0 0 0 0 0 1 1 0;]
% Row sum for each row index i
Temp=sum(S,2)
for i=1:9
    for j=1:9
    if i~=j
        D(i,j)=0;
    else
        D(i,i)= Temp(i); %Creating D
        
    end
    end
    
  end

 %calculating the Laplacian   
 L=D-S;
 disp(D);
 disp(L);
 [V,Di]=eig(L); %Eigen vectors and corresponding Diagonal Eigen values
 disp(V);
 disp(Di);
 K=[-0.3333   -0.2331    0.5396;-0.3333   -0.2605    0.3046;-0.3333   -0.0432    0.3984;-0.3333   -0.3234   -0.2367;-0.3333   -0.3507   -0.4717; -0.3333   -0.1335   -0.3778;-0.3333    0.3940    0.0733;-0.3333    0.3666   -0.1617;-0.3333    0.5838   -0.0679]
 idx=kmeans(K,3); %K means for smallest 3 eigen values
 disp(idx); %returns the index for clustering for row indices