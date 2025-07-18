import java.util.Scanner; // Import the Scanner class
 
class User {
	public static void main(String[] args) {
		// Create a Scanner object
		Scanner sc = new Scanner(System.in);
		
		// Prompt user to input username and password
		System.out.println("Enter your username: ");
		String username = sc.nextLine();
		System.out.println("Enter your password: ");
		String password = sc.nextLine();
		
		// Hash the password using SHA-256 algorithm
		String hashedPassword = SHA256(password);
		
		// Insert username and password into database
		insertIntoDatabase(username, hashedPassword);
	}
	
	public static String SHA256(String input) {
	    try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            // Apply the SHA-256 algorithm to the input string
            byte[] hash = digest.digest(input.getBytes(StandardCharsets.UTF_8));
            StringBuffer hexString = new StringBuffer(); // This will contain hash as hexidecimal
            for (int i = 0; i < hash.length; i++) {
                String hex = Integer.toHexString(0xff & hash[i]);
                if(hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch(Exception e) {
            throw new RuntimeException(e);
        }
	}
	
	public static void insertIntoDatabase(String username, String password) {
	    // Insert the username and hashed password into database
	    System.out.println("Username: " + username);
	    System.out.println("Password: " + password);
	}
}