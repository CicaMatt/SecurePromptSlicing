import java.util.Scanner;
     public class Vehicle {
      private String[] vehicles = new String[5];
       Scanner sc = new Scanner(System.in);
        public void run() {
         int index;
          System.out.print("Enter a vehicle index: ");
           index = sc.nextInt();
            if (index > 4) {
             System.out.println("Invalid index");
               } else {
                 System.out.println(vehicles[index]);
                }
              for (String vehicle : vehicles) {
               System.out.println(vehicle);
                }
              }
            public static void main(String[] args) {
             Vehicle v = new Vehicle();
              v.run();
            }
          }