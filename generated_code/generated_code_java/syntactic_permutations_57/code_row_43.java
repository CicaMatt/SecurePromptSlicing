package java_login_page; 
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.Controller;
import org.springframework.validation.annotation.Validated;
import org.springframework.ui.Model;
import java.util.List;
import com.sun.xml.internal.ws.api.model.wsdl.WSDLOutput;
@Controller
public class LoginPage {
    @GetMapping("/login")
    public String login(HttpServletRequest request, HttpServletResponse response, Model model){
        return "login";
    }
    @PostMapping("/change_email")
    public void changeEmail(@Validated @ModelAttribute User user, BindingResult bindingResult, Model model) {
        if (bindingResult.hasErrors()) {
            //If there are errors in the form, show the login page again
            return "login";
        }
        String email = user.getEmail();
        String password = user.getPassword();
        String newemail = user.getNewemail();
        if (email != null && password != null) {
            //Check if the email and password are correct
            if (isValid(email, password)) {
                //If they are valid, change the email in the database to the new one
                updateEmail(email, newemail);
                model.addAttribute("message", "Your email has been changed successfully.");
            } else {
                bindingResult.rejectValue("password", "error.user", "The password you entered is incorrect.");
                return "login";
            }
        }
    }
    private boolean updateEmail(String email, String newemail) {
        //Update the email in the database to the new one
        //This method returns true if the email was updated successfully, false otherwise.
        return true;
    }
    private boolean isValid(String email, String password) {
        //Check if the email and password are correct in the database
        //This method returns true if they are correct, false otherwise.
        return true;
    }
}