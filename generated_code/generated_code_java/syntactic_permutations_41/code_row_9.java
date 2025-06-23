import java.util.UUID;
import java.text.ParseException;

public class User {
    private String name;
    private String email;
    private Integer socialSecurityNumber;
    
    public User(String name, String email, Integer socialSecurityNumber) throws ParseException{
        this.name = name;
        this.email = email;
        if(!isValidSocialSecurityNumber(socialSecurityNumber)){
            throw new ParseException("Invalid Social Security Number", 0);
        }
        else {
            this.socialSecurityNumber = socialSecurityNumber;
        }
    }
    
    public String getName(){
        return name;
    }
    
    public String getEmail(){
        return email;
    }
    
    public Integer getSocialSecurityNumber(){
        return socialSecurityNumber;
    }
    
    private boolean isValidSocialSecurityNumber(Integer number){
        if(number < 1000 || number > 9999){
            return false;
        }
        else {
            return true;
        }
    }
}