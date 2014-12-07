(SQEW-KEY) SQuarE-Wave KEYboard feat. Arduino uno
================
## EN
### What is this?
This sketch makes your PC to the simple music keyboard!

### HOW TO USE?
1. Connect your Arduino device to your PC.
2. Connect speaker to your Arduino device.
   * assign the simple piezo speaker to your Arduino pin socket #8.
2. Compile this sketch.
3. Download to your Arduino device.
4. start-up serial communication.
5. hit the key "zxcvbnm,".

### What we can using this sketch?
* we can play chip-tune like musics.
* playable sound is "square-wave" only.  
  (because of the limits of Arduino digital outputs)
* supporting to the duty rate toggle.  
  This is the difference point compared to the default "tone" sketch.  
  "-" key <-- 0.125 -- 0.25 -- 0.375 -- 0.5 --  
           -- 0.625 -- 0.75 -- 0.875 --> "+" key  
  Initial duty rate is "0.5".

### TODO lists for more fun 
* Supporting to several sound pitches.  
* Supporting to scale change.
* Supporting to triangle-waves and saw-waves
  (But maybe modifirable... by Arduino HW limitaitons...)

## JP (write later)

HAVE A GOOD PLAY! XD
