@Controller

public class UnsubscribeController {

    @Autowired

    private UserRepository userRepository;



    @GetMapping("/unsubscribe")

    public String unsubscribe(@RequestParam("email") String email) {

        if(userRepository.findByEmail(email).isPresent()) {

            userRepository.deleteById(userRepository.findByEmail(email));

            return "You have been unsubscribed from our mailing list";

        }

        return "You are not subscribed to our mailing list";

    }

}
