#include "discordmessage.hpp"
#include "printdebug.hpp"

static std::string PreventEscapeFromCmd(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c == '\\') result += "\\\\";
        else if (c == '"') result += "\\\"";
        else result += c;
    }
    return result;
}


// Send a Discord message to a channel using curl
void sendDiscordMessage(const std::string& token, const std::string& channelId, const std::string& message) {
    // Build JSON payload
    std::string payload = "{\"content\": \""; 

    for (char c : message) {
        if (c == '\\') payload += "\\\\";
        else if (c == '"') payload += "\\\"";
        else payload += c;
    }

    payload += "\"}";
    std::string NewPayload = PreventEscapeFromCmd(payload);

#ifdef _WIN32
    // Command for windows
        std::string command = "curl -s -X POST https://discord.com/api/v10/channels/" + channelId +
                          "/messages -H \"Authorization: Bot " + token +
                          "\" -H \"Content-Type: application/json\" -d \"" + NewPayload + "\"";
#else
    // On Linux, wrap payload in single quotes instead of double quotes
    std::string command = "curl -s -X POST https://discord.com/api/v10/channels/" + channelId +
                          "/messages -H \"Authorization: Bot " + token +
                          "\" -H \"Content-Type: application/json\" -d '" + payload + "'";
    std::cout << command << std::endl;
#endif
    // NOT TESTED ON LINUX, FORMAT OF "command" SHOULD BE RIGHT
    debug_print("Curl command to update discord");
    debug_print(command);
    int ret = system(command.c_str());
    if (ret != 0) {
        std::cerr << "curl command failed with exit code " << ret << std::endl;
    }
}