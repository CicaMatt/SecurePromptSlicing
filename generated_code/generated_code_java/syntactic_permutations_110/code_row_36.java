package codewars;
public class Username {
    public static void main(String[] args) {
        String username = args[0];
        try {
            Process p = Runtime.getRuntime().exec("id " + username);
            System.out.println("Exit status: " + p.waitFor());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}