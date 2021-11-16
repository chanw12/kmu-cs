package project;

import java.util.Random;
public class CSMACD {

    
      public static void main(String[] args) {
          Random rand = new Random();
          int attemptnum = 0;
          int collision;
          int busy = rand.nextInt(10);
          boolean transmit = false;
          int max_Attempt = 15;
          System.out.println("Attempt: " + attemptnum);
          while(attemptnum < max_Attempt)
          {
              collision = rand.nextInt(2);
              if(busy != 1)
                  busy = rand.nextInt(10);
              int ing = rand.nextInt(8); // 전송을 계속 하고 있는지 판별s
              
              if(busy > 2) // busy가 2보다크면 채널이 busy상태인걸로 간주
              {
                  System.out.println("busy");
                  continue;
              }
              else
              {
                 
                 busy = 1;
                 System.out.println("Transmit and receive...");
                 if(ing == 0 || collision ==0) // ing == 0 ->전송이 끝났다 , collision ==0 -> collision이 발생했다.
                 {
                     if(collision == 0 )
                     {
                         System.out.println("Collision detected");
                         
                         attemptnum++;
                         
                         if(attemptnum < max_Attempt)
                         {
                             System.out.println("Send a jamming signal");
                             double num2 = Math.pow(2,attemptnum);
                             int waittime = rand.nextInt(((int)num2-1));
                             System.out.println("wait" + waittime +"ms" );
                             try{
                                 Thread.sleep(1*waittime);
                             }catch (InterruptedException e){
                                 e.printStackTrace();
                             }
                             System.out.println("Attempt: " + attemptnum);
                             busy = 0;
                         }     
                         continue;
                         
                     }
                     else
                     {
                         System.out.println("Transmit Success");
                         transmit = true;
                         break;
                     }
                 }
                 else
                 {
                     continue;
                 }
                  
              }
              
          }
          if(transmit == false)
              System.out.println("Transmit fail");
          
          
          
          
          
          
          
      }
}