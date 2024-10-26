so in this assingment we are going to send requests from the client to the server porgram
the server has to create a named pipe and will wait for requests sent over the named pipe
the client will request in this format range XX(lower bound) YY(upper bound)
the server is supposed to get the requeset and compute all the prime numbers from lower bound to upperbound
if the request malformed the server will return a "malformed request" msg.
- the fifo special file can be opened and written by multiple files
- the fifo must be opened on both sides before data can be passed
- fifo blocks until the other end is opened also
- the client side only opens fifo on write only mode (myfifo, O_WRONLY)
- while the server side first opens for read only mode (myfifo, O_RDONLY)

- okay so i ran the current program it did communicate but the arr i asssigned
    did not pass any value maybe becuase i am stupid oh i see it now

