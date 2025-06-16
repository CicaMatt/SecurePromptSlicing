import java.util.Scanner;

class Main{
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter a command");
    String s = sc.nextLine();
    executeCmd(s);
  }
  
  private static void executeCmd(String cmd){
    Runtime rt = Runtime.getRuntime();
    Process p = rt.exec(cmd);
    p.waitFor();
    System.out.println("Command executed");
  }
}