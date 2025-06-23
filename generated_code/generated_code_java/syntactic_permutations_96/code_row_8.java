import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public class RegistrationForm {
	private String username;
	private String password;
	private String hashedPassword;
	
	public static void main(String[] args) throws NoSuchAlgorithmException {
		RegistrationForm form = new RegistrationForm("username", "password");
		form.hashPassword();
		System.out.println("Hashed password: " + form.getHashedPassword());
	}

	public RegistrationForm(String username, String password) {
		this.username = username;
		this.password = password;
	}
	
	public void hashPassword() throws NoSuchAlgorithmException {
		MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] messageDigest = md.digest(password.getBytes());
        
        String salt = generateSalt();
        md.update((salt + password).getBytes());
        hashedPassword = bytesToHex(messageDigest);
	}
	
	public static String generateSalt() {
		Random random = new Random();
		StringBuilder salt = new StringBuilder();
		for(int i=0; i<16; i++) {
			salt.append(Integer.toString(random.nextInt()));
		}
		return salt.toString();
	}
	
	public static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (int i = 0; i < hash.length; i++) {
            String hex = Integer.toHexString(0xff & hash[i]);
            if(hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
	
	public String getHashedPassword() {
		return hashedPassword;
	}
}