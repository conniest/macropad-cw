As of 6/5/2025 the nullbits macropad works to turn breakin on/off, keyer on/off,
and increment/decrement speed.

This is implemented as a set of application shortcuts in xfce4-keyboard-settings for the on/off items,
along with a speed daemon (speedy) that handles the rotary encoder.

TO ENABLE THE USE OF THE MACROPAD

1. First compile custom keymap in the macropad firmware to send the desired keycodes and reflash the macropad 
(qmk/keyboards/nullbitsco/scramble/keymaps/connie/keymap.c).  Right now speedy assumes F13-F16 for breakin
and keyer on/off keys and F15, F19 and F20 on the rotary encoder.

2. Second fix up xmodmap and run it as follows:  xmodmap ./xmodmap-new .  Copy it to ~/.Xmodmap and make sure your .bashrc
includes a line like /usr/bin/xmodmap ~/.Xmodmap to make it take effect on every login.   This is necessary to avoid collisions with the function keys implemented on the macropad.  Not running xmodmap is a common cause for speedy to not work.

3. Third set up the shortcuts in keyboard settings to map keysyms on the macropad to CAT commands to radio
for breakin on/off and keyer on/off.
These shortcuts are stored in ~/.config/xfce4/xfconf/xfce-perchannel-xml/xfce4-keyboard-shortcuts.xml.  (Windows or
other desktop users will have to find their desktop keymapper and adjust accordingly.)

      <property name="F18" type="string" value="sh -c &apos;echo -n KS018\;  &gt; /dev/ttyUSB0&apos;"/>
      <property name="F17" type="string" value="sh -c &apos;echo -n BI0\;  &gt; /dev/ttyUSB0&apos;"/>
      <property name="F14" type="string" value="sh -c &apos;echo -n BI1\;  &gt; /dev/ttyUSB0&apos;"/>
      <property name="F13" type="string" value="sh -c &apos;echo -n KR1\;  &gt; /dev/ttyUSB0&apos;"/>
      <property name="F16" type="string" value="sh -c &apos;echo -n KR0\;  &gt; /dev/ttyUSB0&apos;"/>


These steps so far handle the breakin and keyer on/off functions.

4. Finally start the daemon that handles the rotary encoder 
sudo ./speedy   # assumes radio on ttyUSB0 right now.   To change, need to recompile.  Someday will make this more dynamic.
Also can start as a service.    speedy --debug will stay on the commandline and print debugging output.

This daemon is necessary because there is no cat command to directly increment
or decrement the keyer speed, and doing get-increment-set with a keyboard shortcut is too slow
for a rotary encoder to work reasonably well.


######
Notes on testing CAT commands with the echo method.

1. lsof /dev/ttyUSB0   #  to check that there are no programs holding it
2.  cat < /dev/ttyUSB0   # in one terminal.  Output will show up here
3. echo -n 'ID;' > /dev/ttyUSB0    # issue commands in a separate terminal

also turned off flow control in the radio.  This didn't matter

# *****  Use echo and socat to get result in same terminal

echo -n 'ID;' | socat - FILE:/dev/ttyUSB0,raw,echo=0,b38400     # works, prints result

#### Serial terminal works but there is a gotcha --

opening a serial terminal on /dev/ttyUSB0 with port parameters 8N1 38400 works 
BUT you can't just type in the terminal or even cut and paste from another window into the terminal
with a right-click.  Have to paste with the terminal "Paste" menu command

not sure but some cruft is getting sent through, maybe having to do with line endings.  Needs further
investigation


