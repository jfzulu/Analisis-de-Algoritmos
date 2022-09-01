#=function MM_Aux(dims,i,j,S)

 if j <= i + 1
    return 0
  end
   
  min = Inf

  if S[i,j]==0

    for k in i + 1: j-1
 
      numMult = MM_Aux(dims, i, k,S)
 
      numMult += MM_Aux(dims, k+1, j,S)
 
      numMult += dims[i] * dims[k] * dims[j]
 
      if numMult < min
        min = numMult
      end
    end

    S[i,j]=min
    
  end
  

  return S[i,j]
end=#

function backtracking(B,s,e)

  if s+1 == e

    return "A"*string(s)*" A"*string(e)
  end
  if (s == e )
     return "A"*string(s)
  end
  
  pos = Int(B[s,e])
  cadenaA = backtracking(B,s,pos)
  cadenaB = backtracking(B,pos+1,e)

  return "("*cadenaA*")("* cadenaB*")"
  
end


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
        
        numMult = S[i,k] + S[k + 1,j] + d[i ] * d[k+1] * d[j+1]
        
        if numMult < S[i,j]
          S[i,j] = numMult
          B[i,j] = k
        end
        
      k = k + 1
        
      end
    end
  end
  display(S)
  
  println(backtracking(B, 1,length(d)-1))
  return S[1,n-1]
end

d=[84,24,5,10,100,5,50]

@time println("El numero minimo de multiplicaciones es  "* string(MM(d)))