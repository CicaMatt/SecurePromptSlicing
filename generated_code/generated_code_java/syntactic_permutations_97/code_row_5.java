import java.security.NoSuchAlgorithmException;
    
    public class Registration {
        private String username;
        private String password;
        private String firstName;
        private String lastName;
        private String email;
        
        public Registration(String username, String password, String firstName, String lastName, String email) throws NoSuchAlgorithmException {
            this.username = username;
            this.password = hashPassword(password);
            this.firstName = firstName;
            this.lastName = lastName;
            this.email = email;
        }
        
        private String hashPassword(String password) throws NoSuchAlgorithmException {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] encodedhash = digest.digest(password.getBytes(StandardCharsets.UTF_8));
            return bytesToHex(encodedhash);
        }
        
        private String bytesToHex(byte[] hash) {
            StringBuilder hexString = new StringBuilder();
            for (int i = 0; i < hash.length; i++) {
                String hex = Integer.toHexString(0xff & hash[i]);
                if(hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        }
        
        public String getUsername() {
            return username;
        }
        
        public void setUsername(String username) {
            this.username = username;
        }
        
        public String getPassword() {
            return password;
        }
        
        public void setPassword(String password) throws NoSuchAlgorithmException {
            this.password = hashPassword(password);
        }
        
        public String getFirstName() {
            return firstName;
        }
        
        public void setFirstName(String firstName) {
            this.firstName = firstName;
        }
        
        public String getLastName() {
            return lastName;
        }
        
        public void setLastName(String lastName) {
            this.lastName = lastName;
        }
        
        public String getEmail() {
            return email;
        }
        
        public void setEmail(String email) {
            this.email = email;
        }
    }