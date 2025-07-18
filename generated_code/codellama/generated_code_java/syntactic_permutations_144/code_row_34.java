public class Unsubscribe {
    public static void main(String[] args) {
        String email = "test@example.com";
        
        if (!checkIfEmailExistsInDatabase(email)) {
            System.out.println("0");
            return;
        }
        
        if (unsubscribeScriptReturns1()) {
            System.out.println("1");
        } else {
            System.out.println("2");
        }
    }

    static boolean checkIfEmailExistsInDatabase(String email) {
        // Check if the email exists in the database
        return false;
    }

    static boolean unsubscribeScriptReturns1() {
        // Call a script that unsubscribes the email
        return true;
    }
}