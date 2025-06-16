package io.github.easymodeling.modeler.provider;
    
    import java.util.Optional;
    
    public class LoginService {
      private static final String SUCCESS = "success";
      private static final String CANT_LOGIN = "cant_login";
      private static final String INTERNAL_SERVER_ERROR = "internal_server_error";
    
      private UserRepository userRepository;
      private LoginView view;
    
      public void login(String username, String password) {
        try {
          Optional<User> optionalUser = userRepository.findByUsernameAndPassword(username, password);
          if (optionalUser.isPresent()) {
            view.redirect(SUCCESS);
          } else {
            view.redirect(CANT_LOGIN);
          }
        } catch (Exception e) {
          view.redirect(INTERNAL_SERVER_ERROR);
        }
      }
    }