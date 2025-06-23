import java.security.*;

public class User {
	private String username, password;
	
	public User(String username, String password) {
		this.username = username;
		try{
			MessageDigest digest = MessageDigest.getInstance("SHA-256");
		    byte[] hash = digest.digest(password.getBytes("UTF-8"));
		    this.password = bytesToHex(hash); 
		}catch(Exception e){
			throw new RuntimeException("Error in hashing the password");
		}
	}
	
	private static String bytesToHex(byte[] hash) {
        StringBuffer hexString = new StringBuffer();
	    for (int i = 0; i < hash.length; i++) {
	      String hex = Integer.toHexString(0xff & hash[i]);
	      if(hex.length() == 1) hexString.append('0');
	        hexString.append(hex);
	    }
	    return hexString.toString();
  	}
}