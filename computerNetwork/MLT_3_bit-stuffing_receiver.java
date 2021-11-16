package project;
import java.util.Scanner;
public class receiver {

    /**
     * @param args
     */
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        String input;
        input = sc.next();
        String arr = "";
        
        for(int i=0;i<input.length();i++)
        {
            if(i==0 && input.charAt(i)=='+')
            {
                arr += "1";
                continue;
            }
            if(i==0 && input.charAt(i) == '0')
            {
                arr += "0";
                continue;
            }
            if(input.charAt(i)!= input.charAt(i-1))
            {
                arr += "1";
            }
            else{
                arr += "0";
            }
            
        }
        System.out.println(arr);
        
        String number;
        number = arr;
        String number1 = "";
        int temp=0;
        int start = 0;
        
        while(number.contains("11111"))
        {
            start = 0;
            temp = number.indexOf("11111");
            number1 += number.substring(start,temp);
            number1 += "11111";
            temp +=6;
            start = temp;
            number = number.substring(start,number.length());
            
        }
        number1 += number;
        System.out.println(number1);
        
    }
}
    