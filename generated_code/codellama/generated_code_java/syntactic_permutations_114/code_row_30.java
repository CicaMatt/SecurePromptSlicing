java.util.Scanner;
class SystemUtility {
   public static void main(String args[]) {
      Scanner sc = new Scanner(System.in);
      String s = sc.nextLine();
      try{
         Process p=Runtime.getRuntime().exec("ls "+s);
         p.waitFor();
         System.out.println("Successfully executed command!");
       } catch (Exception e) {
          System.out.println(e);
        }
   }
}