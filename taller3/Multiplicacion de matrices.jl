#=function MM_Aux(dims,i,j,S)

 if j <= i + 1
    return 0
  end
   
  min = Inf

  if S[i,j]==0

    for k in i + 1: j-1
 
      cost = MM_Aux(dims, i, k,S)
 
      cost += MM_Aux(dims, k+1, j,S)
 
      cost += dims[i] * dims[k] * dims[j]
 
      if cost < min
        min = cost
      end
    end

    S[i,j]=min
    
  end
  

  return S[i,j]
end=#


function MM(d)
    S = [0.0 for i=1:length(d), j = 1 : length(d)+1]   
    B = [0.0 for i=1:length(d), j = 1 : length(d)+1]   
    #return (MM_Aux(d,1,length(d),S))
  
    n = length(d)
  
  
    for l in 2: n+1     
   
      for i in 1: n - l + 2
   
        j = i + l -1
  
        S[i,j] = Inf
  
   
        k = i
        while j < n && k <= j 
          
          cost = S[i,k] + S[k + 1,j] + d[i ] * d[k+1] * d[j+1]
          
          if cost < S[i,j]
            S[i,j] = cost
            B[i,j] = k
          end
          
        k = k + 1
          
        end
      end
    end
  
    display(S)
    display(B)
    return S[1,n-1]
  end
  
  d=[10,100,5,50]
  println("El numero minimo de multiplicaciones es  "* string(MM(d)))