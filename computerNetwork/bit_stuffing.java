package project;
import java.util.Scanner;
public class bit_stuffing {

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
        
            
                
        
        
        
    }

}
