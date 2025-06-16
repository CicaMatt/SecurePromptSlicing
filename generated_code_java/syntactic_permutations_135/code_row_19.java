package code;

public class Login {
    
    public static boolean checkMod() {
        String userName = getUserName();
        String passWord = getPassword();
        if (userName.equals("admin") && passWord.equals("password")) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        boolean checkMod = checkMod();
        System.out.println(checkMod);
    }
}