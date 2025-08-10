module VectorSum

export vector_sum, run_tests

using Test


function vector_sum(a::Real, x::Real, y::Real, N::Integer)
    a = Float64(a)
    x = Float64(x)
    y = Float64(y)
    N = Int(N)

    xvec = fill(x, N)
    yvec = fill(y, N)
    return a .* xvec .+ yvec
end


function run_tests()
    println("Running tests...")

    # Test 1: if y = 0, result should be a*x
    @test vector_sum(2.0, 3.0, 0.0, 5) == fill(6.0, 5)

    # Test 2: if x = 0, result should be y
    @test vector_sum(2.0, 0.0, 3.0, 5) == fill(3.0, 5)

    # Test 3: doubling x and y doubles the result
    r1 = vector_sum(1.5, 2.0, 3.0, 5)
    r2 = vector_sum(1.5, 4.0, 6.0, 5)
    @test r2 == 2 .* r1

    println("All tests passed.")
end

end # module
