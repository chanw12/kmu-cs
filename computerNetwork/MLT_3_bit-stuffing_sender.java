package project;
import java.util.Scanner;
public class sender {

    /**
     * @param args
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String number;
        number = sc.next();
        String number1 = "";
        int temp=0;
        int start = 0;
        
        while(number.contains("11111"))
        {
            start = 0;
            temp = number.indexOf("11111");
            number1 += number.substring(start,temp);
            number1 += "111110";
            temp +=5;
            start = temp;
            number = number.substring(start,number.length());
            
        }
        number1 += number;
        System.out.println(number1);
        char[] arr2;
        arr2 = new char[1000];
        for(int i=0;i<number1.length()-1;i++){
            if(i==0 && number1.charAt(0)=='0')
            {
                System.out.printf("0");
                arr2[0] = 0;
            }
            if(i==0 && number1.charAt(0)=='1')
            {
                System.out.printf("+");
                arr2[0] = '+';
            }
            if(number1.charAt(i+1)=='0')
            {
                arr2[i+1] = arr2[i];
                System.out.printf("%c",arr2[i+1]);
                continue;
            }
            if(number1.charAt(i+1)=='1' && arr2[i] != '0')
            {
                 arr2[i +1] = '0';
                System.out.printf("%c",arr2[i+1]);
                continue;
            }
            if(number1.charAt(i+1)=='1' && arr2[i] =='0')
            {
                boolean findNon = false;
                for(int j=0; j<arr2.length; j++)
                {
                    if(arr2[j] == '+')
                        findNon = true;
                    if(arr2[j] =='-')
                        findNon = false;
                    
                }
                if(findNon)
                {
                    arr2[i +1] = '-';
                    System.out.printf("%c",arr2[i+1]);
                }else{
                    arr2[i +1] = '+';
                    System.out.printf("%c",arr2[i+1]);
                }
                
            }
            
            
        }   
                
        
        
        
    }

}