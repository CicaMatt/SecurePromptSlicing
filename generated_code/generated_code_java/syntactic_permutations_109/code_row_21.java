import java.util.Scanner;

public class UserInfo {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter username: ");
    String userName = sc.nextLine();
    getUserInfo(userName);
  }
  
  public static void getUserInfo(String userName) {
    try {
      Process p = Runtime.getRuntime().exec("cat /etc/passwd | grep " + userName);
      BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
      
      String line;
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}