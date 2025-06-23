# Minecraft-Discord-Bot
Pings minecraft server and updates a discord channel when players join/leave

First create a discord bot and find the targetted channel's id. Information to create/find these can be found here: https://discordpy.readthedocs.io/en/stable/discord.html.

Put these inside the bot.txt file under their corresponding lines. Also update the example.com to your servers ip and cooldown to your desired update interval.

Now you can compile the bot using Makefile (change compiler if you don't use g++), run "make compile_bot" in the src directory to create serverbot.exe.

Now run serverbot.exe, as long as the program runs you'll keep updating the discord channel.

(As of now readsettings.cpp/hpp and settings.txt aren't used, you can ignore them)
