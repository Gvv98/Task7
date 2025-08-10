include("sum_vector.jl")
using .VectorSum  
if length(ARGS) != 4
    println("Usage: julia mainsum.jl <a> <x> <y> <N>")
    exit()
end

a = parse(Float64, ARGS[1])
x = parse(Float64, ARGS[2])
y = parse(Float64, ARGS[3])
N = parse(Int, ARGS[4])

# Test
run_tests()

# Sum
println("\nNow computing a sample vector sum:")
d = vector_sum(a, x, y, N)

println("Parameters: a=$a, x=$x, y=$y, N=$N")
println("First 5 elements of result:")
println(d[1:min(5, end)])
