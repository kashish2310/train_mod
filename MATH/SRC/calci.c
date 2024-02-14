int calci(int a, int b, int op)
{
	//char op;
       //	scanf("%c",&op);
	switch(op){
		case 1 : return add(a,b);
			  

                case 2 : return sub(a,b);
                          
                
                case 3 :return  multiply(a,b);
                          
                 
               case 4 :return div(a,b);
                        
                case 5 :return  mod(a,b);
                       

	        default:
			  return 0;
	}
	
}



