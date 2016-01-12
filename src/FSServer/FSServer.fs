namespace FSServer
open System.Threading.Tasks
open System.Threading


type FSServer() = 
    let mutable _delay=0
    let mutable _input=""

    member this.Delay with set(value) = _delay <- value
    member this.Input with set(value) = _input <- value
  

    member this.returnInputAsync()=  
        Task.Factory.StartNew(fun()-> 
            Thread.Sleep(_delay)
            _input)
       
        
         
    