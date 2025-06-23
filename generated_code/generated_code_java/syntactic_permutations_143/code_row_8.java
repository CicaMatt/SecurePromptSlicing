@RestController
@RequestMapping("/unsubscribe")
public class UnsubscribeController {
  @Autowired
  private UserRepository userRepository;

  @GetMapping()
  public String unsubscribe(@RequestParam("email") String email) {
    Optional<User> user = userRepository.findByEmail(email);
    if (user.isPresent()) {
      userRepository.deleteById(user.get().getId());
      // Unsubscribe from mailing list
      return "You have been successfully unsubscribed";
    } else {
      return "You are not subscribed";
    }
  }
}