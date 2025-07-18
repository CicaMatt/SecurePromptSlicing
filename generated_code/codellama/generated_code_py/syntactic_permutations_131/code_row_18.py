def render_response_from_env(env):
    return env.get_template('foo').render()
