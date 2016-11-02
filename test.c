//Pour arrêter l'utilisation du port serie par linux
//https://github.com/lurch/rpi-serial-console
//==> sudo  rpi-serial-console disable


//Bug: sur NetBeans 8.1, l'appui sur la touche entrée est nécessaire dans la fenêtre "output"
// Dans le projet (Run), la console doit être sur "Standard output"

#include <stdio.h>
#include <unistd.h>   //Used for UART
#include <fcntl.h>   //Used for UART
#include <termios.h>  //Used for UART

#include <string.h>
#include <stdlib.h>

#include "remoteData.h"
//#include "LineFollowing.h"

int uart0_filestream = -1;

void initUART(void)
{
  //-------------------------
  //----- SETUP USART 0 -----
  //-------------------------
  //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively


  //OPEN THE UART
  //The flags (defined in fcntl.h):
  //	Access modes (use 1 of these):
  //		O_RDONLY - Open for reading only.
  //		O_RDWR - Open for reading and writing.
  //		O_WRONLY - Open for writing only.
  //
  //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
  //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
  //											immediately with a failure status if the output can't be written immediately.
  //
  //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
  uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode
  if (uart0_filestream == -1)
  {
    //ERROR - CAN'T OPEN SERIAL PORT
    printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
  }

  //CONFIGURE THE UART
  //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
  //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
  //	CSIZE:- CS5, CS6, CS7, CS8
  //	CLOCAL - Ignore modem status lines
  //	CREAD - Enable receiver
  //	IGNPAR = Ignore characters with parity errors
  //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
  //	PARENB - Parity enable
  //	PARODD - Odd parity (else even)
  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; //<Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);

}

void writeUART(void)
{
  //----- TX BYTES -----
  unsigned char tx_buffer[20];
  unsigned char *p_tx_buffer;

  p_tx_buffer = &tx_buffer[0];
  *p_tx_buffer++ = 'H';
  *p_tx_buffer++ = 'e';
  *p_tx_buffer++ = 'l';
  *p_tx_buffer++ = 'l';
  *p_tx_buffer++ = 'o';

  if (uart0_filestream != -1)
  {
    int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0])); //Filestream, bytes to write, number of bytes to write
    if (count < 0)
    {
      printf("UART TX error\n");
    }
  }

}

void readUART(void)
{
  //----- CHECK FOR ANY RX BYTES -----
  if (uart0_filestream != -1)
  {
    // Read up to 255 characters from the port if they are there
    unsigned char rx_buffer[256];
    int rx_length = read(uart0_filestream, (void*) rx_buffer, 255); //Filestream, buffer to store in, number of bytes to read (max)
    if (rx_length < 0)
    {
      //An error occured (will occur if there are no bytes)
    }
    else if (rx_length == 0)
    {
      //No data waiting
    }
    else
    {
      //Bytes received
      rx_buffer[rx_length] = '\0';
      printf("%i bytes read : %s\n", rx_length, rx_buffer);
      fflush(stdout);
    }
  }
}

int getcUART(void)
{
  char l_car[2];

  //----- CHECK FOR ANY RX BYTES -----
  if (uart0_filestream != -1)
  {

    int rx_length = read(uart0_filestream, (void*) l_car, 1); //Filestream, buffer to store in, number of bytes to read (max)

    if (rx_length < 0)
    {
      //An error occured (will occur if there are no bytes)
      return (-1);
    }
    else if (rx_length == 0)
    {
      //No data waiting
      return (-1);
    }
    else
    {
      //Bytes received
      return l_car[0];
    }
  }
}

void closeUART(void)
{
  //----- CLOSE THE UART -----
  close(uart0_filestream);
}

void writeDebugFrame(char * p_frame, int p_length)
{
  /*
      int i;
      for (i = 0; i < p_length; i++) {
          printf("-%x-", p_frame[i]&0xFF); 
      }

      fflush(stdout);         
   */


  if (uart0_filestream != -1)
  {
    int count = write(uart0_filestream, p_frame, p_length); //Filestream, bytes to write, number of bytes to write

    /*
                            printf("%d / %d bytes write\n", count,p_length);
                            fflush(stdout);                
     */

    if (count < 0)
    {
      //printf("UART TX error\n");
    }
  }
}



struct termios orig_termios;

void reset_terminal_mode()
{
  tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
  struct termios new_termios;

  /* take two copies - one for now, one for later */
  tcgetattr(0, &orig_termios);
  memcpy(&new_termios, &orig_termios, sizeof (new_termios));

  /* register cleanup handler, and set the new terminal mode */
  atexit(reset_terminal_mode);
  cfmakeraw(&new_termios);
  tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
  struct timeval tv = {0L, 0L};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
  int r;
  unsigned char c;
  if ((r = read(0, &c, sizeof (c))) < 0)
  {
    return r;
  }
  else
  {
    return c;
  }
}

int main(int argc, char**argv)
{
  int i;
  int l_car;
  int l_key;
  int l_power1 = 0;
  int l_power2 = 0;
  int coder_left = 0;
  int coder_right = 0;


  // Disable output and input buffering.
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);

  set_conio_terminal_mode();


  /*
      printf("Arguments:\n");
      for (i = 0; i < argc; i++) {
          printf("%i: %s\n", i, argv[i]);
      }
   */
  printf("Start test UART\n\r");


  initUART();

  do
  {
    l_key = 0;

    l_car = getcUART();
    if (l_car >= 0)
    {
      /*
                  printf("-%x-\n\r",l_car&0xFF);
                  fflush(stdout);
       */

        if (remoteOnReceive((char) l_car))
        {
              if (remoteGetDataNumber() == 50)
              {
                coder_right = remoteGetValue()->m_valueS32;
                printf("Coder_right = %lx        \n\r",coder_right);
                fflush(stdout);
              }
              
              if (remoteGetDataNumber() == 51)
              {
                coder_left = remoteGetValue()->m_valueS32;
                printf("coder_left = %lx        \n\r",coder_left);
                fflush(stdout);
              }
        }
        
    }
    else
    {
      usleep(10);
    }

    if (kbhit() != 0) l_key = getch();


    switch (l_key)
    {
    case 'z':
      l_power1 += 500;
      l_power2 += 500;
      remoteDataS16(1, l_power1);
      remoteDataS16(2, l_power2);
      break;
      case 's':
      l_power1 -= 500;
      l_power2 -= 500;
      remoteDataS16(1, l_power1);
      remoteDataS16(2, l_power2);
      break;
      case 'q':
      l_power1 -= 500;
      l_power2 += 500;
      remoteDataS16(1, l_power1);
      remoteDataS16(2, l_power2);
      break;
      case 'd':
      l_power1 += 500;
      l_power2 -= 500;
      remoteDataS16(1, l_power1);
      remoteDataS16(2, l_power2);
      break;
      case 'c':
      l_power1 = 0;
      l_power2 = 0;
      remoteDataS16(1, l_power1);
      remoteDataS16(2, l_power2);
      break;
    }


  }
  while (l_key != 0x1b);


  reset_terminal_mode();

  closeUART();
  printf("Stop test UART\n");

  return 0;
}
