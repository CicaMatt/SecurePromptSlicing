import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class PasswordHashing {
	private String username;
	private String password;
	private String salt;
	
    public PasswordHashing(String username, String password) throws NoSuchAlgorithmException {
		this.username = username;
		this.password = password;
		salt = generateSalt();
	}
	
    private static byte[] hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(password.getBytes());
        md.update(salt.getBytes());
        return md.digest();
    }
	
    private static String generateSalt() {
        byte[] salt = new byte[16];
        Random rand = new Random();
        rand.nextBytes(salt);
        return new String(salt);
    }
    
    public String getPassword() throws NoSuchAlgorithmException{
		byte[] hashedPassword = hashPassword(password, salt);
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < hashedPassword.length; i++) {
            sb.append(Integer.toString((hashedPassword[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
	}
    
    public void saveToDB() throws NoSuchAlgorithmException {
		String hashedPassword = getPassword();
        //save username and hashedPassword to database
    }
}