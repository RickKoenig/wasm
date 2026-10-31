(module
    (func $log (import "imports" "log_func") (param i32))

    (memory (export "memory") 1 10)
    (data (i32.const 0x0) "\ff\01\00\00")

    (func $avg 
     (param $one i32)
     (param $two i32) 
     (param $three i32) 
     (result i32) 
        local.get $one
        local.get $two
        local.get $three
        i32.add
		i32.add
		i32.const 3
		i32.div_u
	)

    (func $log_avg 
     (param $one i32) 
     (param $two i32) 
     (param $three i32)
        local.get $one
        local.get $two
        local.get $three
        call $avg
        call $log
    )

    (export "avg" (func $avg))
    (export "log_avg" (func $log_avg))
)
