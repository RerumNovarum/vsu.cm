︠aaea4ef2-7823-42ec-9742-4b927b0e63ffi︠
%md
Лабораторные работы №6-7
========================
«Интегралы и дифференциальные уравнения»
----------------------------------------

### Вариант №3
︡45cf3fb4-61fa-4db5-a888-b2bf3cbdb3d8︡︡{"done":true,"md":"Лабораторные работы №6-7\n========================\n«Интегралы и дифференциальные уравнения»\n----------------------------------------\n\n### Вариант №3"}
︠4ef93d6e-0055-4df9-a662-02ee60f617b9s︠
%sage
def show_integral(f, F, variables, prefix=''):
    """show_integral(f, F, variables)
f, F: functions of same variables
variables: either list of variables
                or list of tuples of the form
                (v, lo, hi) where v is variable and (lo, hi) are integration limits
prefix: some text you wanna put before integral, such as "$S$ = "
"""
    assert isinstance(variables, list) or isinstance(variables, tuple)
    assert len(variables)     # Why do you need this assert? You check it on the next line.
    if isinstance(variables[0], tuple):
        limits_hi = {str(v):hi for v,lo,hi in variables}
        limits_lo = {str(v):lo for v,lo,hi in variables}
        variables = tuple(v for v,lo,hi in variables)
        integrals = []
        for v in variables[::-1]:
            lo, hi = limits_lo[str(v)], limits_hi[str(v)]
            integrals.append(r"\int_{%s}^{%s}"%(latex(lo), latex(hi)))
        integr = " ".join(integrals)
        differential = " ".join(r"\mathrm{d}%s"%v for v in variables)
        integrand  = f(*variables)
        right = F.limit(**limits_hi)(*variables) - F.limit(**limits_lo)(*variables)
        right_add = ""
    else:
        integr = r"\int"
        differential = " ".join(r"\mathrm{d}%s"%v for v in variables)
        integrand = f(*variables)
        right = F(*variables)
        right_add = "$+ \mathrm{const}$"
    show(prefix, "$%s$"%integr, integrand, "$%s = $"%differential, right, right_add)

︡d7dc2671-ba47-426d-8da7-352f893fd8aa︡︡{"done":true}
︠6195c706-b763-4a66-bec1-2549b5f61ff5i︠
%md
#### Задание №1
Найти первообразную
︡d50ddbba-faa2-493b-b43d-f1336a1c761f︡︡{"done":true,"md":"#### Задание №1\nНайти первообразную"}
︠0a4d4bb1-91cc-4fc1-9644-d5edd32845c5si︠
f(x) = 1/sqrt(4-x^2) + 1/sqrt(4+x^2)
F = f.integral(x)
show_integral(f, F, (x,))
︡ff0ca3db-df79-4766-a795-d0014f1610bc︡︡{"html":"<div align='center'> $\\int$ $\\displaystyle \\frac{1}{\\sqrt{x^{2} + 4}} + \\frac{1}{\\sqrt{-x^{2} + 4}}$ $\\mathrm{d}x = $ $\\displaystyle \\arcsin\\left(\\frac{1}{2} \\, x\\right) + {\\rm arcsinh}\\left(\\frac{1}{2} \\, x\\right)$ $+ \\mathrm{const}$</div>"}︡{"done":true}
︠3320560d-8442-4439-916e-0a9999324655i︠
%md
#### Задание №2
Вычислить определённый интеграл
︡11403b51-7164-4c41-87c4-cb42a12e1520︡︡{"done":true,"md":"#### Задание №2\nВычислить определённый интеграл"}
︠ee656379-38d4-4207-b4fc-d114ff1c1859si︠

f(x) = sin(x) * cos(x) ^ 2
dom_x = (x, 0, pi/2)
f(x) = sin(x) * cos(x)^2
dom_x = (x, 0, pi/2)
F = f.integral(x)
show_integral(f, F, (dom_x,))
︡dadd3483-ac4e-427c-9726-3444224db320︡︡{"html":"<div align='center'> $\\int_{0}^{\\frac{1}{2} \\, \\pi}$ $\\displaystyle \\cos\\left(x\\right)^{2} \\sin\\left(x\\right)$ $\\mathrm{d}x = $ $\\displaystyle \\frac{1}{3}$ </div>"}︡{"done":true}
︠9fa56897-fa51-4148-8c92-ba606b24aa98i︠
%md
#### Задание №3
Вычислить несобственный интеграл
︡3a44dba3-f5a3-462e-99fd-91bddef1965e︡︡{"done":true,"md":"#### Задание №3\nВычислить несобственный интеграл"}
︠beda9493-6d91-49d7-a5ca-7a8cd5537009si︠
f(x) = (3*x^3 + 2*x + 3)/(x^5 + 3*x^4 + 2*x^3)
dom_x = (x, 1, +oo)
F = f.integrate(x)
show_integral(f, F, (dom_x,))
︡2669c795-32ff-4820-9eb9-bad00d1485e9︡︡{"html":"<div align='center'> $\\int_{1}^{+\\infty}$ $\\displaystyle \\frac{3 \\, x^{3} + 2 \\, x + 3}{x^{5} + 3 \\, x^{4} + 2 \\, x^{3}}$ $\\mathrm{d}x = $ $\\displaystyle \\frac{25}{8} \\, \\log\\left(3\\right) - 2 \\, \\log\\left(2\\right) - \\frac{1}{2}$ </div>"}︡{"done":true}
︠8d2f1135-59d0-488f-acfd-ea2ebecf46f6i︠
%md
#### Задание №4
Вычислить площадь фигуры ограниченной прямыми
$\{(x,y) ; y=x^3\}$,
$\{(x,y) ; y=8 \}$ и
$\{(x,y) ; x=0 \}$
︡05b10fc4-cd5e-4077-9cab-2e0f168dec9e︡︡{"done":true,"md":"#### Задание №4\nВычислить площадь фигуры ограниченной прямыми\n$\\{(x,y) ; y=x^3\\}$,\n$\\{(x,y) ; y=8 \\}$ и\n$\\{(x,y) ; x=0 \\}$"}
︠06400ae2-cc9d-4d10-b919-046fec33c21ds︠
forget()
f(x) = x^3
f1(x) = 8
assume(x, 'real')
x_0 = 0
x_1 = (f1 == f).solve(x)[0].right()
S = (f1 - f).integral(x, x_0, x_1)
show_integral(f1 - f, (f1-f).integral(x), [(x, x_0, x_1)], '$S$ = ')
︡0b9fd97d-1d19-49cb-a258-00e44749afe1︡︡{"html":"<div align='center'>$S$ =  $\\int_{0}^{2}$ $\\displaystyle -x^{3} + 8$ $\\mathrm{d}x = $ $\\displaystyle 12$ </div>"}︡{"done":true}
︠409a984b-74ed-44e1-8088-027dd5eb20cci︠
%md
#### Задание №5
Площадь фигуры, заключённой между кривыми, заданными уравнениями
︡f01ae350-fe25-440c-b573-65a1d9d3ff3e︡︡{"done":true,"md":"#### Задание №5\nПлощадь фигуры, заключённой между кривыми, заданными уравнениями"}
︠093af764-06dd-42bc-9ccb-947b4bdab3b3is︠
x, y, a = var('x y a')
eq_1 = x*y   == 4*a^2
eq_2 = 2*x+y == 6*a
assume(a>0)
a_0 = 5
dom_x = (x, 4, 15)
dom_y = (y, 4, 25)
implicit_plot(eq_1.substitute(a=a_0), dom_x, dom_y, color='red') + implicit_plot(eq_2.substitute(a=a_0), dom_x, dom_y)
︡82799fc1-900a-4e6a-9615-41f22586f944︡︡{"file":{"filename":"/projects/c2952ae9-48cd-400a-932b-589f3581fb7a/.sage/temp/compute3-us/6775/tmp__3UCz1.svg","show":true,"uuid":"6902f2a0-efe5-44d3-80ed-34856aedacbb"},"once":false}︡{"html":"<div align='center'></div>"}︡{"done":true}
︠718954c7-01ad-4a1d-a000-0097e56d77dais︠
# well these specific implicit functions
# can be easily transformed to be explicit functions
y_1(x) = eq_1.solve(y).pop().right()
y_2(x) = eq_2.solve(y).pop().right()
intersections = [x_eq.right() for x_eq in (y_1 == y_2).solve(x)]
x_0, x_1 = intersections # there is only two intersections
S = (y_2 - y_1).integral(x, x_0, x_1).canonicalize_radical()
show("$S=$", S)
show("Note, that we had to use .canonicalize_radical() to simplify expression")
︡4830a40b-483f-4965-b72a-9227659b69a7︡︡{"html":"<div align='center'>$S=$ $\\displaystyle -a^{2} {\\left(4 \\, \\log\\left(2\\right) - 3\\right)}$</div>"}︡{"html":"<div align='center'>Note, that we had to use .canonicalize_radical() to simplify expression</div>"}︡{"done":true}
︠37a1aea0-ee87-4b90-bb8d-66cfc7220e44i︠
# let's delete it?
x, y, a = var('x y a')
f1(x) = 4*a^2 / x
f2(x) = 6*a - 2 * x
assume(a>0)
x_0, x_1 = [eq.right() for eq in (f1 == f2).solve(x)]
s = (f2 - f1).integrate(x).canonicalize_radical()
show_integral((f2 - f1), s, [(x, x_0, x_1)], prefix='$S$ = ')  # This way it works
show(s.canonicalize_radical())  # It's form of simplification that works!
︡8cf102ae-955b-4792-b35b-c1478497ef90︡︡{"html":"<div align='center'>$S$ =  $\\int_{a}^{2 \\, a}$ $\\displaystyle 6 \\, a - \\frac{4 \\, a^{2}}{x} - 2 \\, x$ $\\mathrm{d}x = $ $\\displaystyle -4 \\, a^{2} \\log\\left(2 \\, a\\right) + 4 \\, a^{2} \\log\\left(a\\right) + 3 \\, a^{2}$ </div>"}︡{"html":"<div align='center'>$\\displaystyle x \\ {\\mapsto}\\ -4 \\, a^{2} \\log\\left(x\\right) + 6 \\, a x - x^{2}$</div>"}︡{"done":true}
︠e1c296integrall-45e3-8db8-04c3a9c0fd21i︠
%md
#### Задание №6
Вычислить
$\iint\limits_\Omega \mathrm{sgn}(x^2 + y^2 - 4) \mathrm{d}x\mathrm{d}y$

Где
$\Omega = \{ (x,y) ; x^2 + y^2 \leq 9 \}$
︡11885809-6df2-4516-b751-ec7a59bd648e︡︡{"done":true,"md":"#### Задание №6\nВычислить\n$\\iint\\limits_\\Omega \\mathrm{sgn}(x^2 + y^2 - 4) \\mathrm{d}x\\mathrm{d}y$\n\nГде\n$\\Omega = \\{ (x,y) ; x^2 + y^2 \\leq 9 \\}$"}
︠25a643e9-a5f0-4475-9e84-37837e0b7f4e︠
# TODO: rewrite with manual handling of discontinuity
# In short: correct answer is coincidence
#           SAGE doesn't handle it
# Details: https://rerumnovarum.github.io/sage/2016/04/09/discontinuous.html

x, y, r, phi = var('x y r phi')
f(x, y) = sign(x^2 + y^2 - 4)
T(r, phi) = [r*cos(phi), r*sin(phi)]
J = diff(T).det().simplify_full()
T_f = f.substitute(x=T[0], y=T[1])
int_f = integral(integral(T_f*abs(J), r, 0, 3), phi, 0, 2*pi).simplify_full()
show(r"$\iint\limits_\Omega%s = %s$"%(latex(f(x)), latex(int_f)))
︡74ef1ca3-f2b9-429f-98d2-6878ce8a76e0︡︡{"html":"<div align='center'>$\\iint\\limits_\\Omega\\mathrm{sgn}\\left(x^{2} + y^{2} - 4\\right) = \\pi$</div>"}︡{"done":true}
︠3231f5fc-6eb1-4aa9-9381-bcd1c4d867aci︠
%md
#### Задание №7
Найти площадь части поверхности
$z^2 = 2xy$,
отсекаемой плоскостями
$x+y=2$,
$x=0$,
$y=0$
︡1bdba0fd-7754-4be4-9ce0-912fb4701c08︡︡{"done":true,"md":"#### Задание №7\nНайти площадь части поверхности\n$z^2 = 2xy$,\nотсекаемой плоскостями\n$x+y=2$,\n$x=0$,\n$y=0$"}
︠b3b9e5d0-646e-4ec1-9c16-1e4c0b2499ccs︠
forget()
x,y,z = var('x y z')
surf_eq = z^2 == 2*x*y
bounds = [x+y==2, x==0, y==0]
p = implicit_plot3d(surf_eq, (x, -4, 4), (y, -4, 4), (z, -4, 4))
for j, bb in enumerate(bounds):
    p += implicit_plot3d(bb,\
                         (x, -4, 4), (y, -4, 4), (z, -4, 4),\
                         color = hue(pi*j),\
                         legend_label='$%s$'%latex(bb))
p.show()
for bb in bounds:
    i = solve([surf_eq, bb], x, y, z)
    show(i)
︡d004c756-52f3-491c-8d96-b1702b9f88a7︡︡{"file":{"filename":"59579de1-0dd6-41f3-9f61-fed90169b5a9.sage3d","uuid":"59579de1-0dd6-41f3-9f61-fed90169b5a9"}}︡{"html":"<div align='center'></div>"}︡{"html":"<div align='center'>[[$\\displaystyle x = r_{1}$, $\\displaystyle y = -r_{1} + 2$, $\\displaystyle z = -\\sqrt{-2 \\, r_{1}^{2} + 4 \\, r_{1}}$], [$\\displaystyle x = r_{2}$, $\\displaystyle y = -r_{2} + 2$, $\\displaystyle z = \\sqrt{-2 \\, r_{2}^{2} + 4 \\, r_{2}}$], [$\\displaystyle x = 0$, $\\displaystyle y = 2$, $\\displaystyle z = 0$]]</div>"}︡{"html":"<div align='center'>[[$\\displaystyle x = 0$, $\\displaystyle y = r_{3}$, $\\displaystyle z = 0$]]</div>"}︡{"html":"<div align='center'>[[$\\displaystyle x = r_{4}$, $\\displaystyle y = 0$, $\\displaystyle z = 0$]]</div>"}︡{"done":true}
︠43945768-7e99-4e85-bb64-953b74f1e377s︠
x, y, z = var('x y z')
assume(x, y, z, 'real')
parts = surf_eq.solve(z)
sol = 0
for p in parts:
    f_z(x, y) = p.right()
    ds = sqrt(1 + f_z.diff(x)^2 + f_z.diff(y)^2)
    # integrating over [0,2] sometimes fails
    # maybe because of discontinuity
    # (but then why it works other times)
    # Not sure, but probably we can just exclude them
    # it's the same as if we modified function
    # to assign zero to points of discontinuity
    # and these functions gonna be Almost-Everywhere equal
    # i.e. integrals gonna be equal
    assume(x!=2)
    int_ = integral(integral(ds, y, 0, abs(2 - x)), x, 0, 2)
    sol += int_
show('$S=$', sol)
︡bd1ea730-e832-456f-999e-ee9a1c296511︡︡{"html":"<div align='center'>$S=$ $\\displaystyle 2 \\, \\sqrt{2} \\pi$</div>"}︡{"done":true}
︠9e470f04-7fcc-4a84-bf13-f6695b30c833i︠
%md
#### Задание №10
Найти общее решение уравнения $y = xy\prime - {y\prime}^2$
︡a16844b4-7fc3-4c22-a456-5d9caded84af︡︡{"done":true,"md":"#### Задание №10\nНайти общее решение уравнения $y = xy\\prime - {y\\prime}^2$"}
︠d5b42bc5-40bf-45a5-aafb-763daec1d6dais︠
# Please, fix the diff signs. Just ' is bad and I don't know correct command
x = var('x')
y = function('y')(x)
eq = x * y.diff(x) - y.diff(x) ** 2 == y
sols = desolve(eq, y, contrib_ode=True) # maxima can't solve it without contrib_ode=True; it's ok
for s in sols:
    show(s)

︡6da7b706-6972-4b81-a36b-4e0d639c2136︡︡{"html":"<div align='center'>$\\displaystyle y\\left(x\\right) = -C^{2} + C x$</div>"}︡{"html":"<div align='center'>$\\displaystyle y\\left(x\\right) = \\frac{1}{4} \\, x^{2}$</div>"}︡{"done":true}
︠5cbe962c-4617-4694-86d1-4ea65904e332i︠
%md
#### Задание №11
Найти решение дифференциального уравнения $x^2y\prime - \cos2y = 1$, удовлетворяющее условию $y(+\infty) = 9\pi/4$
︡ee14c3ec-1758-4178-98d0-6315829e2bbf︡︡{"done":true,"md":"#### Задание №11\nНайти решение дифференциального уравнения $x^2y\\prime - \\cos2y = 1$, удовлетворяющее условию $y(+\\infty) = 9\\pi/4$"}
︠4e80680d-d68c-4210-9dce-a17d17a05faes︠
forget()
x = var('x')
Y = function('Y')(x)
eq = x^2*Y.diff(x) - cos(2*Y) == 1
x_0 = +oo
y_0 = 9 * pi / 4
s = desolve(eq, Y)
show("General solution of DE:")
show(s)
fv = [v for v in s.variables() if not v in [x, Y]][0]
# Nota bene:
# SAGE cannot take a limit at $\infty$
# of unknown symbolic function $y(x)$
# But problem statement implies,
# that $y$ converges as $x\to+\infty$
#
# ODE solution is represented by equation
                         #
y  = var('y')
s  = s.subs(Y(x) == y)
sl = s.limit(x=+oo)
show('In limit:')
show(sl)
show('Substituting $y=%s$:'%latex(y_0))
c  = sl.subs(y=y_0)
show(c)
c, var_c = c.left(), c.right()
show('Solution:')
s = s.subs(**{str(var_c): c}).simplify_full()
show(s)
show('And how do we make SAGE transform it into '\
     r'$\mathrm{arctan}\frac{x-2}{x}$?')
show('Manually...')
show(s.subs(sin(y)/cos(y)/2 == tan(y)/2).solve(y)[0].right().function(x))
# assume([y > 0 , y < pi/2])
# show(s.solve(y))
︡7b5b2958-0621-4323-b771-311a4b82a1c0︡︡{"html":"<div align='center'>General solution of DE:</div>"}︡{"html":"<div align='center'>$\\displaystyle \\frac{\\sin\\left(2 \\, Y\\left(x\\right)\\right)}{2 \\, {\\left(\\cos\\left(2 \\, Y\\left(x\\right)\\right) + 1\\right)}} = C - \\frac{1}{x}$</div>"}︡{"html":"<div align='center'>In limit:</div>"}︡{"html":"<div align='center'>$\\displaystyle \\frac{\\sin\\left(2 \\, y\\right)}{2 \\, {\\left(\\cos\\left(2 \\, y\\right) + 1\\right)}} = C$</div>"}︡{"html":"<div align='center'>Substituting $y=\\frac{9}{4} \\, \\pi$:</div>"}︡{"html":"<div align='center'>$\\displaystyle \\left(\\frac{1}{2}\\right) = C$</div>"}︡{"html":"<div align='center'>Solution:</div>"}︡{"html":"<div align='center'>$\\displaystyle \\frac{\\sin\\left(y\\right)}{2 \\, \\cos\\left(y\\right)} = \\frac{x - 2}{2 \\, x}$</div>"}︡{"html":"<div align='center'>And how do we make SAGE transform it into $\\mathrm{arctan}\\frac{x-2}{x}$?</div>"}︡{"html":"<div align='center'>Manually...</div>"}︡{"html":"<div align='center'>$\\displaystyle x \\ {\\mapsto}\\ -\\arctan\\left(\\frac{2}{x} - 1\\right)$</div>"}︡{"done":true}
︠a6755b96-7347-4e4d-9d34-3530d8f55485i︠
%md
#### Задание №13
︡b364ffb9-4677-4c84-b27b-6602ae3ad57e︡︡{"done":true,"md":"#### Задание №13"}
︠2582c672-f5b8-4ca7-ab87-54934af0d9f0i︠
t = var('t')
T = ode_solver()
# Where is quite strange way to write the system
T.function = lambda t, y: [
    10 * (y[1] - y[0]),
    y[0] * (28 - y[2]) - y[1],
    y[0] * y[1] - y[2] * 8 / 3
]
T.y_0 = [3, 2, 15] # initiate conditions
T.ode_solve(t_span=[0, 30], num_points=10000) # solveing with t \in [0, 30] and 10000 points (to plot)
line3d([p[1] for p in T.solution])

#for i in range(3):
#    T.plot_solution(i=i)

︡159bf316-bf2e-4d82-878d-26a22405f5fd︡︡{"file":{"filename":"50eb7799-4d29-4df3-96ca-4e48f86505e4.sage3d","uuid":"50eb7799-4d29-4df3-96ca-4e48f86505e4"}}︡{"html":"<div align='center'></div>"}︡{"done":true}
︠5fb7e320-50e7-4a5c-b3ac-f0f1533f7e07i︠
%md
#### Задание №12
За 15 дней распалось 50% радиоактивного вещества

Через какое время останется 1% изначального количества вещества?
︡8fc21ccf-58d7-40ec-94a8-0065997d761e︡︡{"done":true,"md":"#### Задание №12\nЗа 15 дней распалось 50% радиоактивного вещества\n\nЧерез какое время останется 1% изначального количества вещества?"}
︠e7fd27ec-bb9d-4167-84f1-9a1505003143s︠
forget()
l  = var('l')
hl = 15 # decay half-life, days
n  = function('n')(x)
eq = n.diff(x) == -l*n
n  = desolve(eq, n, ivar=x)
show('$n(x)=$', n)
show("Here $C$ is actually initial amount of material")
show("And $l$ is somehow related to half-life")
︡8de7706d-734f-46c1-a004-0fa609ffc46a︡︡{"html":"<div align='center'>$n(x)=$ $\\displaystyle C e^{\\left(-l x\\right)}$</div>"}︡{"html":"<div align='center'>Here $C$ is actually initial amount of material</div>"}︡{"html":"<div align='center'>And $l$ is somehow related to half-life</div>"}︡{"done":true}
︠2826980c-995d-420e-a185-6657aec67c06s︠
freevar = [v for v in n.variables() if not v in (x, l)][0]
eq_hl = n(x=0)/2 == n(x=15)
show("Actually, that's how they're related:", eq_hl)
assume(l>0)
ll = [s.right().simplify_full() for s in eq_hl.solve(l) if s.right().imag() == 0][0]
show('$l=$', ll)
N(x) = freevar*e^(-ll*x)
eq_main = N(x=x) == .01*N(0)
t_0 = eq_main.solve(x)[0].right().simplify_full()
show("Here's our final answer:")
show('$t_0=$', t_0, r'$\approx$', ceil(t_0)) # technically, we need ceil instead of round
︡da0c437a-34ea-43e1-9440-80017bcf35c0︡︡{"html":"<div align='center'>Actually, that's how they're related: $\\displaystyle \\frac{1}{2} \\, C = C e^{\\left(-15 \\, l\\right)}$</div>"}︡{"html":"<div align='center'>$l=$ $\\displaystyle \\frac{1}{15} \\, \\log\\left(2\\right)$</div>"}︡{"html":"<div align='center'>Here's our final answer:</div>"}︡{"html":"<div align='center'>$t_0=$ $\\displaystyle \\frac{15 \\, \\log\\left(100\\right)}{\\log\\left(2\\right)}$ $\\approx$ $\\displaystyle 100$</div>"}︡{"done":true}
︠f9bdc2c6-6258-4424-a158-d759ab40d92f︠









